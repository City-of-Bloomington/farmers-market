<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Space $this->space
 */
use Blossom\Classes\View;

$name = View::escape($this->space->getName());
$title = $this->space->getId() ? $this->_('space_edit') : $this->_('space_add');
?>
<h2><?php echo $title; ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/spaces/update">
    <fieldset>
        <input name="space_id" type="hidden" value="<?php echo $this->space->getId(); ?>" />
        <table>
            <tr><td><label for="name"><?php echo $this->_('name'); ?></label></td>
                <td><input name="name" id="name" value="<?php echo $name; ?>" /></td>
            </tr>
        </table>

        <?php
            $h = $this->template->getHelper('saveAndCancelButtons');
            echo $h->saveAndCancelButtons(BASE_URI.'/spaces');
        ?>
    </fieldset>
</form>
