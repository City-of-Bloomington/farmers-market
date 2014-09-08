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
<h2><?php
        echo $this->_(['vendor', 'vendors', 2]);
        $userCanEdit = Person::isAllowed('vendors', 'edit');
		if ($userCanEdit) {
			$helper = $this->template->getHelper('buttonLink');
			echo $helper->buttonLink(
				BASE_URI.'/vendors/update',
				$this->_('vendor_add'),
				'add'
			);
		}
	?>
</h2>
<table>
	<thead>
		<tr><th></th>
			<th><?php echo $this->_('name'); ?></th>
			<th><?php echo $this->_('address'); ?></th>
			<th><?php echo $this->_('county'); ?></th>
			<th><?php echo "{$this->_('city')}, {$this->_('state')} {$this->_('zip')}"; ?></th>
			<th><?php echo $this->_('phone'); ?></th>
			<th><?php echo $this->_(['email', 'emails', 1]); ?></th>
			<th><?php echo $this->_('website'); ?></th>
		</tr>
	</thead>
	<tbody>
	<?php
		$fields = ['name', 'address', 'city', 'county', 'state', 'zip', 'phone', 'email', 'website'];
		foreach ($this->vendors as $vendor) {
            $editButton = '';
            if ($userCanEdit) {
                $editButton = $helper->buttonLink(
                    BASE_URI.'/vendors/update?vendor_id='.$vendor->getId(),
                    $this->_('vendor_edit'),
                    'edit'
                );
            }
			foreach ($fields as $f) {
				$get = 'get'.ucfirst($f);
				$$f = View::escape($vendor->$get());
			}
			$url = BASE_URI.'/vendors/view?vendor_id='.$vendor->getId();
			echo "
			<tr><td>$editButton</td>
				<td><a href=\"$url\">$name</a></td>
				<td>$address</td>
				<td>$county</td>
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
