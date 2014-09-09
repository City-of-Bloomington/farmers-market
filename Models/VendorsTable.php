<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\TableGateway;
use Zend\Db\Sql\Select;

class VendorsTable extends TableGateway
{
    protected $columns = [
        'id', 'name', 'website', 'address', 'city', 'county', 'state', 'zip', 'phone', 'email'
    ];

	public function __construct() { parent::__construct('vendors', __namespace__.'\Vendor'); }

    /**
     * @param array $fields
     * @param string|array $order Multi-column sort should be given as an array
     * @param bool $paginated Whether to return a paginator or a raw resultSet
     * @param int $limit
     */
    public function find($fields=null, $order='name', $paginated=false, $limit=null)
    {
        return parent::find($fields, $order, $paginated, $limit);
    }
}
