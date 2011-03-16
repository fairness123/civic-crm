<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param string $this->location
 */
if ($this->location) {
	$url = new URL(BASE_URL.'/locations/viewLocation.php?location='.$this->location);
	$location = View::escape($this->location);
	$neighborhoods = Location::getNeighborhoodAssociations($this->location);

	echo "
	<div class=\"locationInfo\">
		<h1><a href=\"$url\">$location</a></h1>
	";

	if (count($neighborhoods)) {
		echo "
		<h2>Neighborhood Associations</h2>
		<ul>
		";
			foreach ($neighborhoods as $neighborhood) {
				$neighborhood = View::escape($neighborhood);
				echo "<li>$neighborhood</li>";
			}
		echo "
		</ul>
		";
	}
	echo "
	</div>
	";

	$constituents = new PersonList(array('address'=>$this->location));
	if (count($constituents)) {
		echo "
		<div class=\"locationResidents\">
			<h2>Associated Residents</h2>
			<ul>
			";
				foreach ($constituents as $person) {
					$url = BASE_URL.'/people/viewPerson.php?person_id='.$person->getId();
					$name = View::escape($person->getFullname());
					echo "<li><a href=\"$url\">$name</a></li>";
				}
			echo "
			</ul>
		</div>
		";
	}
}