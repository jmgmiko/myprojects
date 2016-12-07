<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Table of Airlines</title>
        <link rel="stylesheet" href="css/bootstrap.css">
        <link rel="stylesheet" href="CSS Files/SQLStyle.css">
    </head>
    <body>
        <div class="container-fluid">
            <div class="row">
                <div class="col-md-4 col-md-offset-1 col-xs-12 text-justify block">
                    <h1>This is a list of airlines I know and their respective countries 
                        and alliances.<br><h1 class="text-center">Happy reading!</h1></h1>
                </div>
                <div class="col-md-6 col-xs-12 block">
                    <table class="table table-condensed table-striped table-bordered text-justify">
                        <tbody>
                            <th>Name</th>
                            <th>Country</th>
                            <th>Alliance</th>
                            <?php include 'table_create.php'; ?>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </body>
</html>