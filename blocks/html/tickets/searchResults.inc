<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param TicketList $this->ticketList
 */
$url = new URL(BASE_URL.'/tickets/viewTicket.php');
echo "
<div class=\"searchResults\">
<h1>$this->title</h1>
<table>
	<thead>
		<tr><th>Ticket #</th>
			<th>Categories</th>
			<th>Status</th>
			<th>Location</th>
			<th>Opened Date</th>
			<th>Entered By</th>
		</tr>
	</thead>
	<tbody>
";
	foreach ($this->ticketList as $ticket) {
		$enteredDate = $ticket->getEnteredDate('m-d-y');
		$status = View::escape($ticket->getStatus());
		$enteredBy = $ticket->getEnteredByPerson() ? View::escape($ticket->getEnteredByPerson()->getFullname()) : '';
		$location = View::escape($ticket->getLocation());
		$url->ticket_id = $ticket->getId();
		foreach ($ticket->getIssues() as $issue) {
			echo "
			<tr><td><a href=\"$url\">{$ticket->getId()}</a></td>
				<td>
			";
					$categories = $ticket->getCategories();
					if (count($categories)) {
						echo '<ul>';
						foreach ($categories as $category) {
							$name = View::escape($category);
							echo "<li>$name</li>";
						}
						echo '</ul>';
					}
			echo "
				</td>
				<td>$status</td>
				<td>$location</td>
				<td>$enteredDate</td>
				<td>$enteredBy</td>
			</tr>
			";
		}
	}
echo "
	</tbody>
</table>
</div>
";