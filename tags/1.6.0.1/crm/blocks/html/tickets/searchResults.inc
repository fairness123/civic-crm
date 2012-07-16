<?php
/**
 * Displays a list of Tickets
 *
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if ($this->template->outputFormat == 'html' && !isset($_GET['fields']['number'])) {
	$_GET['fields']['number'] = 1;
}
$ticketList = new TicketList();
$ticketList->findRawData($_GET);

echo "
<div class=\"searchResults\">
";
	if (count($ticketList)) {
		$page = isset($_GET['page']) ? (int)$_GET['page'] : 0;
		$ticketList = $ticketList->getPaginator(50,$page);

		echo "<table>";
		$header = new Block(
			'tickets/partials/searchResultsColumnHeaders.inc',
			array('ticketList'=>$ticketList)
		);
		echo $header->render('html',$this->template);
		echo "</table>";

		$body = new Block(
			'tickets/partials/searchResultsRows.inc',
			array('ticketList'=>$ticketList)
		);
		echo $body->render('html',$this->template);
	}
	else {
		echo "<p>No cases found<p>";
	}
echo "
</div>
";

if ($ticketList instanceof Zend_Paginator) {
	$block = new Block('pageNavigation.inc',array('paginator'=>$ticketList));
	echo $block->render('html',$this->template);
}