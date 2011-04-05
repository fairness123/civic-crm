<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$title = $this->issueType->getId() ? 'Edit IssueType' : 'Add IssueType';
?>
<h1><?php echo $title; ?></h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
	<fieldset><legend>IssueType Info</legend>
		<input name="id" type="hidden" value="<?php echo $this->issueType->getId(); ?>" />
		<table>

			<tr><td><label for="name" class="required">Name</label></td>
				<td><input name="name" id="name" value="<?php echo $this->issueType->getName(); ?>" />
				</td>
			</tr>

		</table>
		<?php
			echo $this->template->formButton('Submit','submit','submit');
			echo $this->template->formButton(
				'Cancel','button','cancel',null,"document.location.href='".BASE_URL."/issueTypes';"
			);
		?>
	</fieldset>
</form>