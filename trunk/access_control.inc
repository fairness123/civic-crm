<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$ZEND_ACL = new Zend_Acl();
/**
 * Load the roles from the database
 */
$roles = new RoleList();
$roles->find();
foreach ($roles as $role) {
	$ZEND_ACL = $ZEND_ACL->addRole(new Zend_Acl_Role($role->getName()));
}

/**
 * Declare all the resources
 */
$ZEND_ACL->add(new Zend_Acl_Resource('Users'));
$ZEND_ACL->add(new Zend_Acl_Resource('Departments'));

/**
 * Assign permissions to the resources
 */
// Administrator is allowed access to everything
$ZEND_ACL->allow('Administrator');