<?php
/**
 * @copyright 2014 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;
use Application\Models\Space;
use Application\Models\SpacesTable;
use Blossom\Classes\Controller;
use Blossom\Classes\Block;

class SpacesController extends Controller
{
    private function loadSpace($id)
    {
        try {
            $space = new Space($id);
            return $space;
        }
        catch (\Exception $e) {
            $_SESSION['errorMessages'][] = $e;
            header('Location: '.BASE_URL.'/spaces');
            exit();
        }
    }
    public function index()
    {
        $table = new SpacesTable();
        $list = $table->find();
        $this->template->blocks[] = new Block('spaces/list.inc', ['spaces'=>$list]);
    }

    public function update()
    {
        $space = !empty($_REQUEST['space_id'])
            ? $this->loadSpace($_REQUEST['space_id'])
            : new Space();

        if (isset($_POST['name'])) {
            try {
                $space->handleUpdate($_POST);
                $space->save();

                header('Location: '.BASE_URL.'/spaces');
                exit();
            }
            catch (\Exception $e) {
                $_SESSION['errorMessages'][] = $e;
            }
        }
        $this->template->blocks[] = new Block('spaces/updateForm.inc', ['space'=>$space]);
    }
}
