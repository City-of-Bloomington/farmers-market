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
	private $peopleUpdated = false;

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
        $this->peopleUpdated = false;
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
        if ($this->peopleUpdated) { $this->savePeople(array_keys($this->getPeople())); }
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
	 * Sets the people for this vendor.  Does not save to database
	 *
	 * @param string $ids Comma separated list of person_id's
	 */
	public function setPeople($ids)
	{
        $this->peopleUpdated = true;
        $this->people = [];
        foreach (explode(',', $ids) as $id) {
            $id = (int)$id;

            try {
                $this->people[$id] = new Person($id);
            }
            catch (\Exception $e) {
            }
        }
	}

	/**
	 * Saves the list of vendor_people to the database
	 *
	 * @param array $ids An array of person_id
	 */
	public function savePeople(array $ids)
	{
        if ($this->getId()) {
            $this->people = [];
            $zend_db = Database::getConnection();
            $zend_db->query('delete from vendor_people where vendor_id=?')->execute([$this->getId()]);

            $query = $zend_db->createStatement('insert into vendor_people set vendor_id=?, person_id=?');
            foreach ($ids as $id) {
                $query->execute([$this->getId(), (int)$id]);
            }
        }
	}
}
