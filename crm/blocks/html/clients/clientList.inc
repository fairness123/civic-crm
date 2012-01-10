<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param ClientList $this->clientList
 */
?>
<div class="clientList">
	<h1>Clients
		<?php
			if (userIsAllowed('Clients')) {
				echo $this->template->linkButton(
					'Add',BASE_URL.'/clients/updateClient.php','add'
				);
			}
		?>
	</h1>
	<p>These are authorized clients that are allowed to POST tickets via web services.
		The only web service interface we have right now is Open311.</p>
	<table>
		<thead>
			<tr><th></th><th>ID</th><th>Name</th><th>URL</th><th>Contact</th></tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->clientList as $client) {
				$editButton = '';
				$deleteButton = '';
				if (userIsAllowed('Clients')) {
					$editButton = $this->template->linkButton(
						'Edit',
						BASE_URL."/clients/updateClient.php?client_id={$client->getId()}",
						'edit'
					);
					$deleteButton = $this->template->linkButton(
						'Delete',
						BASE_URL."/clients/deleteClient.php?client_id={$client->getId()}",
						'delete'
					);
				}
				$name = View::escape($client->getName());
				$url = $client->getURL();
				$contact = $client->getContactPerson();
				$contactName = View::escape($contact->getFullname());
				echo "
				<tr><td>$editButton $deleteButton</td>
					<td>{$client->getId()}</td>
					<td>$name</td>
					<td><a href=\"$url\">$url</a></td>
					<td><a href=\"{$contact->getURL()}\">$contactName</a></td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</div>