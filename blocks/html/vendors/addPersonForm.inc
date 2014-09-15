<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vendor $this->vendor
 */
use Blossom\Classes\View;

$this->template->addToAsset('scripts', JQUERY);
$this->template->addToAsset('scripts', BASE_URI.'/js/personChooser.js');
?>
<h2><?php echo $this->_('person_add'); ?></h2>
<form method="post" action="<?php echo BASE_URI; ?>/vendors/addPerson" id="addPersonForm">
    <fieldset>
        <input name="vendor_id" type="hidden" value="<?php echo $this->vendor->getId(); ?>" />
        <table>
            <tr><td><label for="person_id"><?php echo $this->_(['person', 'people', 1]); ?></label></td>
                <td><input name="person_id" id="person_id" value="" />
                    <span id="person-name"></span>
                    <a class="btn" onclick="PERSON_CHOOSER.open('person');">
                        <i class="fa fa-plus"></i>
                        <?php echo $this->_('person_add'); ?>
                    </a>
                </td>
            </tr>
        </table>
        <?php
            $helper = $this->template->getHelper('saveAndCancelButtons');
            echo $helper->saveAndCancelButtons(BASE_URI.'/vendors/view?vendor_id='.$this->vendor->getId());
        ?>
    </fieldset>
</form>
