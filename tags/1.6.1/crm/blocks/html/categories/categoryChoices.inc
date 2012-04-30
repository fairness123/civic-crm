<?php
/**
 * @copyright 2011-2012 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param CategoryList $this->categoryList
 * @param URL $this->return_url
 */
echo "
<div class=\"categoryChoices\">
	<h1>Choose a category</h1>
	<ul>
";
	$return_url = $this->return_url;
	// Preserve any extra parameters passed in
	foreach ($_REQUEST as $key=>$value) {
		if ($key!='return_url') {
			$return_url->$key = $value;
		}
	}
	foreach ($this->categoryList as $category) {
		$name = View::escape($category->getName());
		$description = View::escape(trim($category->getDescription()));
		$return_url->category_id = "{$category->getId()}";
		echo "<li><a href=\"$return_url\" title=\"$description\">$name</a></li>\n";
	}
echo "
	</ul>
</div>
";