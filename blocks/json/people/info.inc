<?php
/**
 * @copyright 2009-2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Person $this->person
 */
use Application\Models\Person;
use Blossom\Classes\View;
use Blossom\Classes\Url;

$person = [
    'id'       => $this->person->getId(),
    'fullname' => $this->person->getFullname(),
    'email'    => $this->person->getEmail()
];
echo json_encode($person);
