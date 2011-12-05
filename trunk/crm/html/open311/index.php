<?php
/**
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
// Grab the format from the file extension used in the url
$request = explode('?',$_SERVER['REQUEST_URI']);
$format = preg_match("/\.([^.?]+)/",$request[0],$matches)
	? strtolower($matches[1])
	: 'html';

$template = isset($_GET['partial'])
	? new Template('partial',$format)
	: new Template('open311',$format);


if (false !== strpos($request[0],'discovery')) {
	$block = new Block('open311/discovery.inc');
}
else {
	$block = isset($_GET['partial'])
		? new Block("open311/$_GET[partial]")
		: new Block('open311/client.inc');
}

$template->blocks[] = $block;
echo $template->render();
