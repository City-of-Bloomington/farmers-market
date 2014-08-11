<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Vendor;
use Application\Models\VendorsTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class VendorsController extends Controller
{
	private function loadVendor($id)
	{
		try {
			$vendor = new Vendor($id);
			return $vendor;
		}
		catch (\Exception $e) {
			$_SESSION['errorMessages'][] = $e;
		}
	}


	public function index()
	{
		$table = new VendorTable();
		$list = $table->find();

		$this->template->blocks[] = new Block('vendors/list.inc', ['vendors'=>$list]);
	}

	public function view()
	{
		$vendor = $this->loadVendor($_REQUEST['vendor_id']);

		$this->template->blocks[] = new Block('vendors/view.inc', ['vendor'=>$vendor]);

	}

	public function update()
	{
		$vendor = !empty($_REQUEST['vendor_id'])
			? $this->loadVendor($_REQUEST['vendor_id'])
			: new Vendor();

		if (isset($_POST['name'])) {
			try {
				$vendor->handleUpdate($_POST);
				$vendor->save();
				header('Location: '.BASE_URL.'/vendors/view?vendor_id='.$vendor->getId());
				exit();
			}
			catch (\Exception $e) {
				$_SESSION['errorMessages'][] = $e;
			}
		}

		$this->templates->blocks[] = new Block('vendors/updateForm.inc', ['vendor'=>$vendor]);
	}
}
