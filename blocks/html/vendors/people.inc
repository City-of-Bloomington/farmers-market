<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vendor $this->vendor
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\Block;
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<h2><?php
        echo $this->_(['person', 'people', 2]).' ';

        $userCanEdit = Person::isAllowed('vendors', 'addPerson');
        if ($userCanEdit) {
            $h = $this->template->getHelper('buttonLink');
            echo $h->buttonLink(
                BASE_URI.'/vendors/addPerson?vendor_id='.$this->vendor->getId(),
                $this->_('person_add'),
                'add'
            );
        }
    ?>
</h2>
<?php
$people = $this->vendor->getPeople();
if (count($people)) {
    echo '<table>';
    foreach ($people as $person) {
        $deleteButton = '';
        if ($userCanEdit) {
            $deleteButton = $h->buttonLink(
                BASE_URI."/vendors/removePerson?vendor_id={$this->vendor->getId()};person_id={$person->getId()}",
                $this->_('person_delete'),
                'delete',
                ButtonLink::SIZE_ICON
            );
        }
        $name     = View::escape($person->getFullname());
        $email    = View::escape($person->getEmail());
        $username = View::escape($person->getUsername());
        echo "
        <tr><td>$name</td>
            <td>$email</td>
            <td>$username</td>
            <td>$deleteButton</td>
        </tr>
        ";
    }
    echo '</table>';
}
?>
