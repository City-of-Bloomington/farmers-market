<?php
/**
 * @copyright 2009-2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
use Blossom\Classes\View;

$fields = array('firstname','lastname','email');
foreach ($fields as $field) {
	$get = 'get'.ucfirst($field);
	$$field = View::escape($this->person->$get());
}
$title = $this->person->getId() ? View::escape('Edit '.$this->person->getFirstname()) : 'Add Someone';
?>
<div class="updatePersonForm">
	<h2><?php echo $title; ?></h2>
	<form method="post" action="<?php echo BASE_URI; ?>/people/update">
		<fieldset><legend><?php echo $this->_('info_person'); ?></legend>
			<input name="person_id"  type="hidden" value="<?php echo $this->person->getId(); ?>" />
			<input name="return_url" type="hidden" value="<?php echo $this->return_url; ?>" />
            <?php
                // Preserve any extra parameters passed in
                foreach ($_REQUEST as $key=>$value) {
                    if (!in_array($key,$fields)) {
                        $key   = View::escape($key);
                        $value = View::escape($value);
                        echo "<input type=\"hidden\" name=\"$key\" value=\"$value\" />\n";
                    }
                }
            ?>
			<table>
				<tr><td><label for="firstname" class="required"><?php echo $this->_('firstname'); ?></label></td>
					<td><input name="firstname" id="firstname" value="<?php echo $firstname; ?>" /></td>
				</tr>

				<tr><td><label for="lastname" class="required"><?php echo $this->_('lastname'); ?></label></td>
					<td><input name="lastname" id="lastname" value="<?php echo $lastname; ?>" /></td>
				</tr>

				<tr><td><label for="email"><?php echo $this->_(['email', 'emails', 1]); ?></label></td>
					<td><input name="email" id="email" value="<?php echo $email; ?>" /></td>
				</tr>
			</table>

            <button type="submit"><span class="fa fa-check"></span> <?php echo $this->_('save'); ?></button>
			<?php
                $onclick = isset($_REQUEST['callback'])
                    ? 'onclick="self.close();"'
                    : '';
                echo "
                <a class=\"btn\" href=\"{$this->return_url}\" $onclick>
                    <span class=\"fa fa-times\"></span>
                    {$this->_('cancel')}
                </a>
                ";
			?>
		</fieldset>
	</form>
</div>
