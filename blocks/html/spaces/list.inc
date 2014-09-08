<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Zend\Db\Result $this->spaces
 */
use Application\Models\Person;
use Application\Templates\Helpers\ButtonLink;
use Blossom\Classes\View;
?>
<h2><?php
        echo $this->_(['space', 'spaces', 2]);
        $userCanEdit = Person::isAllowed('spaces', 'edit');
        if ($userCanEdit) {
            $helper = $this->template->getHelper('buttonLink');
            echo $helper->buttonLink(
                BASE_URI.'/spaces/update',
                $this->_('space_add'),
                'add'
            );
        }
    ?>
</h2>
<table>
    <?php
        foreach ($this->spaces as $space) {
            $editButton = '';
            if ($userCanEdit) {
                $editButton = $helper->buttonLink(
                    BASE_URI."/spaces/update?space_id={$space->getId()}",
                    $this->_('space_edit'),
                    'edit'
                );
            }
            $name = View::escape($space);
            echo "
            <tr><td>$editButton</td>
                <td>$name</td>
            </tr>
            ";
        }
    ?>
</table>
