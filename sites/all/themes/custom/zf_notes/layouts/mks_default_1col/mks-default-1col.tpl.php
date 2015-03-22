<div class="row">
  <div class="large-12 columns"> 
    <div class="row">
      <div class="large-12 columns">

        <nav class="top-bar" data-topbar>
          <ul class="title-area">

            <li class="name">
              <h1>
                <a href="#">
                  Top Bar Title
                </a>
              </h1>
            </li>
            <li class="toggle-topbar menu-icon"><a href="#"><span>menu</span></a></li>
          </ul>

          <section class="top-bar-section">

            <ul class="right">
              <li class="divider"></li>
              <li class="has-dropdown">
                <a href="#">Main Item 1</a>
                <ul class="dropdown">
                  <li><label>Section Name</label></li>
                  <li class="has-dropdown">
                    <a href="#" class="">Has Dropdown, Level 1</a>
                    <ul class="dropdown">
                      <li><a href="#">Dropdown Options</a></li>
                      <li><a href="#">Dropdown Options</a></li>
                      <li><a href="#">Level 2</a></li>
                      <li><a href="#">Subdropdown Option</a></li>
                      <li><a href="#">Subdropdown Option</a></li>
                      <li><a href="#">Subdropdown Option</a></li>
                    </ul>
                  </li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li class="divider"></li>
                  <li><label>Section Name</label></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li class="divider"></li>
                  <li><a href="#">See all →</a></li>
                </ul>
              </li>
              <li class="divider"></li>
              <li><a href="#">Main Item 2</a></li>
              <li class="divider"></li>
              <li class="has-dropdown">
                <a href="#">Main Item 3</a>
                <ul class="dropdown">
                  <li><a href="#">Dropdown Option</a></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li><a href="#">Dropdown Option</a></li>
                  <li class="divider"></li>
                  <li><a href="#">See all →</a></li>
                </ul>
              </li>
            </ul>
          </section>
        </nav>

      </div>
    </div>        
    <div class="row">
      <?php print $content['header'];?>
    </div>
    <div class="row">
      <?php print $content['content'];?>
    </div>
    <footer class="row">
      <div class="large-12 columns"><hr/>
        <div class="row">  
          <?php print $content['footer'];?>
        </div>
      </div>
    </footer>
  </div>
</div>