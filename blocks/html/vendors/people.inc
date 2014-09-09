<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Vendor $this->vendor
 */
use Application\Models\Person;
use Blossom\Classes\Block;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$people = $this->vendor->getPeople();
if (count($people)) {
    foreach ($people as $person) {
        $block = new Block('people/info.inc', ['person'=>$person]);
        echo $block->render('html', $this->template);
    }
}
