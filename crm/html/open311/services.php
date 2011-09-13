<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$person = isset($_SESSION['USER']) ? $_SESSION['USER'] : 'anonymous';

// Grab the format from the file extension used in the url
$format = preg_match("/[^.]+$/",$_SERVER['REQUEST_URI'],$matches)
	? strtolower($matches[0])
	: 'html';
$template = new Template('open311',$format);


// See if they're asking for a particular service
preg_match('|/open311/v2/services/?([0-9a-f]{24})?.*|',$_SERVER['REQUEST_URI'],$matches);
if (isset($matches[1]) && $matches[1]) {
	try {
		$category = new Category($matches[1]);
		if ($category->allowsDisplay($person)) {
			$template->blocks[] = new Block('open311/serviceInfo.inc',array('category'=>$category));
		}
		else {
			// Not allowed to see tickets for this category
		}
	}
	catch (Exception $e) {
		// Unknown service
	}
}
// Just display  the full service list
else {
	$categoryList = new CategoryList();
	$categoryList->find();
	$template->blocks[] = new Block('open311/serviceList.inc',array('categoryList'=>$categoryList));
}
echo $template->render();