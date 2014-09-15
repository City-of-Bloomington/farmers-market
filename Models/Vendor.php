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

	private $people = [];

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

	/**
	 * @Override
	 */
	public function exchangeArray($data)
	{
        parent::exchangeArray($data);

        $this->people = [];
	}

	public function validate()
	{
		if (!$this->getName()) { throw new \Exception('missingRequiredFields'); }
	}

	/**
	 * @Override
	 */
	public function save()
	{
        parent::save();
    }

	//----------------------------------------------------------------
	// Generic Getters & Setters
	//----------------------------------------------------------------
	public function getId     () { return parent::get('id');      }
	public function getName   () { return parent::get('name');    }
	public function getWebsite() { return parent::get('website'); }
	public function getAddress() { return parent::get('address'); }
	public function getCity   () { return parent::get('city');    }
	public function getCounty () { return parent::get('county');  }
	public function getState  () { return parent::get('state');   }
	public function getZip    () { return parent::get('zip');     }
	public function getPhone  () { return parent::get('phone');   }
	public function getEmail  () { return parent::get('email');   }

	public function setName   ($s) { parent::set('name',    $s); }
	public function setWebsite($s) { parent::set('website', $s); }
	public function setAddress($s) { parent::set('address', $s); }
	public function setCity   ($s) { parent::set('city',    $s); }
	public function setCounty ($s) { parent::set('county',  $s); }
	public function setState  ($s) { parent::set('state',   $s); }
	public function setZip    ($s) { parent::set('zip',     $s); }
	public function setPhone  ($s) { parent::set('phone',   $s); }
	public function setEmail  ($s) { parent::set('email',   $s); }

	/**
	 * @param array $post
	 */
	public function handleUpdate($post)
	{
		$fields = [
            'name', 'website', 'address', 'city', 'county', 'state', 'zip', 'phone', 'email',
            'people'
        ];
		foreach ($fields as $f) {
			$set = 'set'.ucfirst($f);
			$this->$set($post[$f]);
		}
	}

	//----------------------------------------------------------------
	// Custom functions
	//----------------------------------------------------------------
	public function getPeople()
	{
        if (!$this->people && $this->getId()) {
            $table = new PeopleTable();
            $list = $table->find(['vendor_id'=>$this->getId()]);
            foreach ($list as $person) {
                $this->people[$person->getId()] = $person;
            }
        }
        return $this->people;
	}

	/**
	 * Create a vendor_people relationship in the database
	 *
	 * @param int $id The person_id to add
	 */
	public function addPerson($id)
	{
        if ($this->getId() && !empty($id)) {
            $person = new Person($id);

            // Update the database
            $zend_db = Database::getConnection();
            $zend_db->query('insert vendor_people set vendor_id=?, person_id=?')
                    ->execute([$this->getId(), $person->getId()]);

            // Update this object's state with the new person
            $people = $this->getPeople();
            $this->people[$person->getId()] = $person;
        }
	}

	/**
	 * Removes a person association from the database
	 *
	 * This only deletes the vendor_people relationship.
	 * This does not delete a person's record from the database.
	 *
	 * @param int $id The person_id to remove
	 */
	public function removePerson($id)
	{
        if ($this->getId() && !empty($id)) {
            $person = new Person($id);

            $zend_db = Database::getConnection();
            $zend_db->query('delete from vendor_people where vendor_id=? and person_id=?')
                    ->execute([$this->getId(), $person->getId()]);

            // Remove the person from this object's state
            $people = $this->getPeople();
            if (isset($this->people[$person->getId()])) {
                unset($this->people[$person->getId()]);
            }
        }
	}
}
