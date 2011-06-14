<?php
/**
 * A collection class for Department objects
 *
 * @copyright 2011 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class DepartmentList extends MongoResultIterator
{
	/**
	 * @param array $fields
	 */
	public function __construct($fields=null)
	{
		parent::__construct();
		if (is_array($fields)) {
			$this->find($fields);
		}
	}

	/**
	 * Populates the collection, using strict matching of the requested fields
	 *
	 * @param array $fields
	 * @param array $order
	 */
	public function find($fields=null,$order=array('name'=>1))
	{
		$search = array();
		if (count($fields)) {
			foreach ($fields as $key=>$value) {
				if ($value) {
					$search[$key] = (string)$value;
				}
			}
		}
		if (count($search)) {
			$this->cursor = $this->mongo->departments->find($search);
		}
		else {
			$this->cursor = $this->mongo->departments->find();
		}
		if ($order) {
			$this->cursor->sort($order);
		}
	}

	/**
	 * Hydrates all the Department objects from a database result set
	 *
	 * This is a callback function, called from ZendDbResultIterator.  It is
	 * called once per row of the result.
	 *
	 * @param int $key The index of the result row to load
	 * @return Department
	 */
	public function loadResult($data)
	{
		return new Department($data);
	}
}
