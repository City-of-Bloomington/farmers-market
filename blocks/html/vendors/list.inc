<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->vendors
 */
use Application\Models\Person;
use Blossom\Classes\View;
?>
<h2>Vendors
	<?php
		if (Person::isAllowed('vendors', 'edit')) {
			$helper = $this->template->getHelper('buttonLink');
			echo $helper->buttonLink(
				BASE_URI.'/vendors/update',
				'Add Vendor',
				'add'
			);
		}
	?>
</h2>
<table>
	<thead>
		<tr><th></th>
			<th>name</th>
			<th>address</th>
			<th>city, state zip</th>
			<th>phone</th>
			<th>email</th>
			<th>website</th>
		</tr>
	</thead>
	<tbody>
	<?php
		$fields = ['name', 'address', 'city', 'state', 'zip', 'phone', 'email', 'website'];
		foreach ($this->vendors as $vendor) {
			foreach ($fields as $f) {
				$get = 'get'.ucfirst($f);
				$$f = View::escape($vendor->$get());
			}
			$editButton = '';
			if (Person::isAllowed('vendors', 'edit')) {
				$editButton = $helper->buttonLink(
					BASE_URI.'/vendors/update?vendor_id='.$vendor->getId(),
					'Edit Vendor',
					'edit'
				);
			}
			echo "
			<tr><td></td>
				<td>$name</td>
				<td>$address</td>
				<td>$city $state $zip</td>
				<td>$phone</td>
				<td>$email</td>
				<td>$website</td>
			</tr>
			";
		}
	?>
	</tbody>
</table>
