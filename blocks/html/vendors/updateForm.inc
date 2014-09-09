<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vendor $this->vendor
 */
use Blossom\Classes\View;

$fields = ['name', 'address', 'city', 'county', 'state', 'zip', 'phone', 'email', 'website'];
foreach ($fields as $f) {
	$get = 'get'.ucfirst($f);
	$$f = View::escape($this->vendor->$get());
}
$people = $this->vendor->getPeople();

$title = $this->vendor->getId() ? 'Edit Vendor' : 'Add Vendor';
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/vendors/update">
	<fieldset><legend><?php echo $this->_('vendor_info'); ?></legend>
		<input name="vendor_id"  type="hidden" value="<?php echo $this->vendor->getId(); ?>" />
		<input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />
		<table>
			<tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
				<td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
			</tr>
			<tr><td><label for="address"><?php echo $this->_('address'); ?></label></td>
				<td><input name="address" id="address" value="<?php echo $address; ?>" /></td>
			</tr>
			<tr><td><label for="city"><?php echo $this->_('city'); ?></label></td>
				<td><input name="city" id="city" value="<?php echo $city; ?>" /></td>
			</tr>
			<tr><td><label for="county"><?php echo $this->_('county'); ?></label></td>
                <td><input name="county" id="county" value="<?php echo $county; ?>" /></td>
            </tr>
			<tr><td><label for="state"><?php echo $this->_('state'); ?></label></td>
				<td><input name="state" id="state" value="<?php echo $state; ?>" size="2" />
					<label for="zip"><?php echo $this->_('zip'); ?></label>
					<input name="zip" id="zip" value="<?php echo $zip; ?>" size="5" />
				</td>
			</tr>
			<tr><td><label for="phone"><?php echo $this->_('phone'); ?></label></td>
				<td><input name="phone" id="phone" value="<?php echo $phone; ?>" /></td>
			</tr>
			<tr><td><label for="email"><?php echo $this->_('email'); ?></label></td>
				<td><input name="email" id="email" value="<?php echo $email; ?>" /></td>
			</tr>
			<tr><td><label for="website"><?php echo $this->_('website'); ?></label></td>
				<td><input name="website" id="website" value="<?php echo $website; ?>" /></td>
			</tr>
		</table>
    </fieldset>
    <fieldset><legend><?php echo $this->_(['person', 'people', 2]); ?></legend>
        <?php
            $people = $this->vendor->getPeople();
            foreach ($people as $person) {
                $name = View::escape($person->getFullname());
                echo "<div>$name</div>";
            }

            $ids = implode(',', array_keys($people));
            echo "<input name=\"people\" id=\"people\" value=\"$ids\" />";
        ?>
    </fieldset>
    <fieldset><legend><?php echo $this->_('submit'); ?></legend>
		<?php
			$helper = $this->template->getHelper('saveAndCancelButtons');
			echo $helper->saveAndCancelButtons($this->return_url);
		?>
	</fieldset>
</form>
