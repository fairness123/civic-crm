<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$person = isset($_SESSION['USER']) ? $_SESSION['USER'] : 'anonymous';

// Grab the format from the file extension used in the url
$format = preg_match("/\.([^.?]+)/",$_SERVER['REQUEST_URI'],$matches)
	? strtolower($matches[0])
	: 'html';
$template = new Template('open311',$format);

// Translate Open311 fields into CRM fields
$open311Fields = array(
	'ticket'=>array(
		'lat'=>'latitude',
		'long'=>'longitude',
		'address_string'=>'location'
	),
	'issue'=>array(

	)
);


// See if they're asking for a particular request (ticket)
preg_match('|/open311/v2/requests/?([0-9a-f]{24})?.*|',$_SERVER['REQUEST_URI'],$matches);
if (isset($matches[1]) && $matches[1]) {
	try {
		$ticket = new Ticket($matches[1]);

		if (isset($_POST)) {
			// Edit an existing ticket
			if (userIsAllowed('Tickets')) {

			}
			else {
				// Not allowed to edit tickets
				$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
			}
		}
		else {
			// Display an existing ticket
			if ($ticket->allowsDisplay($person)) {
				$template->blocks[] = new Block('open311/requestInfo.inc',array('ticket'=>$ticket));
			}
			else {
				// Not allowed to see this ticket
				$_SESSION['errorMessages'][] = new Exception('noAccessAllowed');
			}
		}
	}
	catch (Exception $e) {
		// Unknown ticket
		$_SESSION['errorMessages'][] = $e;
	}
}
else {
	if (!empty($_REQUEST['service_code'])) {
		try {
			$category = new Category($_REQUEST['service_code']);
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
	}
	if (isset($_POST['service_code'])) {
		// Create a new Ticket
		try {
			if (!isset($category)) {
				throw new Exception('missingService');
			}
			if ($category->allowsPosting($person)) {
				$ticket = new Ticket();
				$ticketData = array();
				foreach ($open311Fields['ticket'] as $open311Field=>$crmField) {
					if (isset($_POST[$open311Field])) {
						$ticketData[$crmField] = $_POST[$open311Field];
					}
				}
				$ticket->set($ticketData);

				$issue = new Issue();
				$issueData = array(
					'category'=>$category,
					'customFields'=>$_POST['attribute']
				);
				if (isset($_POST['description'])) {
					$issueData['notes'] = $_POST['description'];
				}
				$issue->set($issueData);

				// Create the History entries
				$open = new History();
				$open->setAction('open');
				$ticket->updateHistory($open);
			}
			else {
				// Not allowed to create tickets for this category
			}
		}
		catch (Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
	}
	else {
		// Do a search for tickets
		$search = array();
		if (isset($category) && $category->allowsDisplay($person)) {
			$search['category'] = $category->getId();
		}
		if (!empty($_REQUEST['start_date'])) {
			$search['start_date'] = $_REQUEST['start_date'];
		}
		if (!empty($_REQUEST['end_date'])) {
			$search['end_date'] = $_REQUEST['end_date'];
		}
		if (!empty($_REQUEST['status'])) {
			$search['status'] = $_REQUEST['status'];
		}
		$ticketList = new TicketList($search);
		$ticketList->limit(1000);
		$template->blocks[] = new Block(
			'open311/requestList.inc',
			array('ticketList'=>$ticketList)
		);
	}
}

echo $template->render();