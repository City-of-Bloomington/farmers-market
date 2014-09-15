<?php
/**
 * @copyright 2009-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\ResultSet $people
 */
use Application\Models\Person;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<div class="interfaceBox">
	<h2><?php
			echo $this->translate(['person','people',2]);

			$return_url = Url::current_url();
			$helper = $this->template->getHelper('buttonLink');

			if (Person::isAllowed('people')) {
				echo $helper->buttonLink(
					BASE_URI."/people/update?return_url=$return_url",
					$this->translate('person_add'),
					'add'
				);
			}
		?>
	</h2>
	<table>
		<thead>
			<tr><th></th>
				<th><?php echo $this->_('username'); ?></th>
				<th><?php echo $this->_('name'); ?></th>
				<th><?php echo $this->_(['email','emails',1]); ?></th>
			</tr>
		</thead>
		<tbody>
		<?php
			foreach ($this->people as $person) {
				$editButton = '';
				if (Person::isAllowed('people')) {
					$editButton = $helper->buttonLink(
						BASE_URI."/people/update?person_id={$person->getId()};return_url=$return_url",
						$this->translate('edit'),
						'edit'
					);
				}

				if (!empty($_REQUEST['callback'])) {
                    $this->template->addToAsset('scripts', JQUERY);
                    $this->template->addToAsset('scripts', BASE_URI.'/js/personChooser.js');

                    $callback = preg_replace('/[^a-zA-Z_\.]/', '', $_REQUEST['callback']);
                    $url = "javascript:self.opener.$callback('{$person->getId()}');";
				}
				else {
                    $url = $person->getUri();
                }

				$name = View::escape($person->getFullname());
				echo "
				<tr><td>$editButton</td>
					<td>{$person->getUsername()}</td>
					<td><a href=\"$url\">$name</a></td>
					<td>{$person->getEmail()}</td>
				</tr>
				";
			}
		?>
		</tbody>
	</table>
</div>
