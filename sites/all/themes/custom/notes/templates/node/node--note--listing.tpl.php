<div class="col-lg-3 col-md-4 col-xs-6 thumb">
  <div class="panel panel-default text-center">
    <div class="panel-heading">
      <h3 class="panel-title note-title note-rate-<?php print lcfirst($_html['rate']);?>"><?php print $_html['title'];?></h3>
    </div>
    <div class="panel-body note-body">
      <?php print $_html['body'];?>
    </div>
    <ul class="list-group">
      <li class="list-group-item note-item"><strong><?php print $_html['end_date'];?></strong></li>
      <li class="list-group-item note-item"><strong><?php print t('Category');?></strong> <?php print $_html['category'];?></li>
      <li class="list-group-item note-item"><a href="#" class="btn btn-primary">Details</a></li>
    </ul>
  </div>
</div>