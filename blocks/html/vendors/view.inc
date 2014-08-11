<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vendor $this->vendor
 */
$fields = ['name', 'address', 'city', 'state', 'zip', 'phone', 'email', 'website'];
foreach ($fields as $f) {
	$get = 'get'.ucfirst($f);
	$$f = View::escape($this->vendor->$get());
}
$editButton = '';
if (Person::isAllowed('vendors', 'edit')) {
	$helper = $this->template->getHelper('buttonLink');
	$editButton = $helper->buttonLink(
		BASE_URI.'/vendors/update?vendor_id='.$this->vendor->getId(),
		'Edit Vendor',
		'edit'
	);
}
echo "
<h2>$name $editButton</h2>
<table>
	<tr><th>address</th><td>$address</td></tr>
	<tr><th>city</th><td>$city $state $zip</td></tr>
	<tr><th>phone</th><td>$phone</td></tr>
	<tr><th>email</th><td>$email</td></tr>
	<tr><th>website</th><td>$website</td></tr>
</table>
