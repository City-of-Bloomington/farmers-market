<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->vendors
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php
        echo $this->_(['vendor', 'vendors', 2]);
        $userCanEdit = Person::isAllowed('vendors', 'edit');
		if ($userCanEdit) {
            $return_url = Url::current_url();

			$helper = $this->template->getHelper('buttonLink');
			echo $helper->buttonLink(
				BASE_URI."/vendors/update?return_url=$return_url",
				$this->_('vendor_add'),
				'add'
			);
		}
	?>
</h2>
<table>
	<tbody>
	<?php
		$fields = ['name', 'address', 'city', 'county', 'state', 'zip', 'phone', 'email', 'website'];
		foreach ($this->vendors as $vendor) {
            $editButton = '';
            if ($userCanEdit) {
                $editButton = $helper->buttonLink(
                    BASE_URI."/vendors/update?vendor_id={$vendor->getId()};return_url=$return_url",
                    $this->_('vendor_edit'),
                    'edit',
                    ButtonLink::SIZE_ICON
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
				<td>$city</td>
				<td>$state</td>
				<td>$zip</td>
			</tr>
			";
		}
	?>
	</tbody>
</table>
