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

$title = $this->vendor->getId() ? 'Edit Vendor' : 'Add Vendor';
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/vendors/update">
	<fieldset><legend>Vendor Info</legend>
		<input name="vendor_id" type="hidden" value="<?php echo $this->vendor->getId(); ?>" />
		<table>
			<tr><td><label for="name"></label></td>
				<td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
			</tr>
			<tr><td><label for="address">address</label></td>
				<td><input name="address" id="address" value="<?php echo $address; ?>" /></td>
			</tr>
			<tr><td><label for="city">city</label></td>
				<td><input name="city" id="city" value="<?php echo $city; ?>" /></td>
			</tr>
			<tr><td><label for="state">state</label></td>
				<td><input name="state" id="state" value="<?php echo $state; ?>" size="2" />
					<label for="zip">zip</label>
					<input name="zip" id="zip" value="<?php echo $zip; ?>" size="5" />
				</td>
			</tr>
			<tr><td><label for="phone">phone</label></td>
				<td><input name="phone" id="phone" value="<?php echo $phone; ?>" /></td>
			</tr>
			<tr><td><label for="email">email</label></td>
				<td><input name="email" id="email" value="<?php echo $email; ?>" /></td>
			</tr>
			<tr><td><label for="website">website</label></td>
				<td><input name="website" id="website" value="<?php echo $website; ?>" /></td>
			</tr>
		</table>
		<?php
			$helper = $this->template->getHelper('saveAndCancelButtons');
			echo $helper->saveAndCancelButtons(BASE_URI.'/vendors');
		?>
	</fieldset>
</form>
