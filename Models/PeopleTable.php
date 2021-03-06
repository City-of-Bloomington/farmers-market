<?php
/**
 * @copyright 2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class PeopleTable extends TableGateway
{
    protected $columns = [
        'id', 'firstname', 'lastname', 'email', 'username', 'authenticationMethod', 'role'
    ];
	public function __construct() { parent::__construct('people', __namespace__.'\Person'); }

	/**
	 * @param array $fields
	 * @param string|array $order Multi-column sort should be given as an array
	 * @param bool $paginated Whether to return a paginator or a raw resultSet
	 * @param int $limit
	 */
	public function find($fields=null, $order='lastname', $paginated=false, $limit=null)
	{
		$select = new Select('people');
		if (count($fields)) {
			foreach ($fields as $key=>$value) {
				switch ($key) {
					case 'user_account':
						if ($value) {
							$select->where('username is not null');
						}
						else {
							$select->where('username is null');
						}
					break;

					case 'vendor_id':
                        $select->join(['v'=>'vendor_people'], 'people.id=v.person_id', []);
                        $select->where([$key=>$value]);
                    break;

					default:
                        if (in_array($key, $this->columns)) {
                            $select->where([$key=>$value]);
                        }
				}
			}
		}
		return parent::performSelect($select, $order, $paginated, $limit);
	}

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function search($fields=null, $order='lastname', $paginated=false, $limit=null)
    {
        $select = new Select('people');
        if (count($fields)) {
            foreach ($fields as $key=>$value) {
                switch ($key) {
                    case 'user_account':
                        if ($value) {
                            $select->where('username is not null');
                        }
                        else {
                            $select->where('username is null');
                        }
                    break;

                    default:
                        if (in_array($key, $this->columns)) {
                            $select->where->like($key, "$value%");
                        }
                }
            }
        }
        return parent::performSelect($select, $order, $paginated, $limit);
    }
}
