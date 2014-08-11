<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;
use Blossom\Classes\ActiveRecord;
use Blossom\Classes\Database;
use Blossom\Classes\ExternalIdentity;

class Vendor extends ActiveRecord
{
	protected $tablename = 'vendors';

	/**
	 * Populates the object with data
	 *
	 * Passing in an associative array of data will populate this object without
	 * hitting the database.
	 *
	 * Passing in a scalar will load the data from the database.
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 *
	 * @param int|string|array $id (ID, email, username)
	 */
	public function __construct($id=null)
	{
		if ($id) {
			if (is_array($id)) {
				$this->exchangeArray($id);
			}
			else {
				$zend_db = Database::getConnection();
				$sql = 'select * from vendors where id=?';
				$result = $zend_db->createStatement($sql)->execute([$id]);
				if (count($result)) {
					$this->exchangeArray($result->current());
				}
				else {
					throw new \Exception('vendors/unknownVendor');
				}
			}
		}
		else {
			// This is where the code goes to generate a new, empty instance.
			// Set any default values for properties that need it here
		}
	}

	public function validate()
	{
		if (!$this->getName()) { throw new \Exception('missingRequiredFields'); }
	}

	public function save() { parent::save(); }

	//----------------------------------------------------------------
	// Generic Getters & Setters
	//----------------------------------------------------------------
	public function getId     () { return parent::get('id');      }
	public function getName   () { return parent::get('name');    }
	public function getWebsite() { return parent::get('website'); }
	public function getAddress() { return parent::get('address'); }
	public function getCity   () { return parent::get('city');    }
	public function getState  () { return parent::get('state');   }
	public function getZip    () { return parent::get('zip');     }
	public function getPhone  () { return parent::get('phone');   }
	public function getEmail  () { return parent::get('email');   }

	public function setName   ($s) { parent::set('name',    $s); }
	public function setWebsite($s) { parent::set('website', $s); }
	public function setAddress($s) { parent::set('address', $s); }
	public function setCity   ($s) { parent::set('city',    $s); }
	public function setState  ($s) { parent::set('state',   $s); }
	public function setZip    ($s) { parent::set('zip',     $s); }
	public function setPhone  ($s) { parent::set('phone',   $s); }
	public function setEmail  ($s) { parent::set('email',   $s); }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$fields = ['name', 'website', 'address', 'city', 'state', 'zip', 'phone', 'email'];
		foreach ($fields as $f) {
			$set = 'set'.ucfirst($f);
			$this->$set($post[$f]);
		}
	}

	//----------------------------------------------------------------
	// Custom functions
	//----------------------------------------------------------------
}
