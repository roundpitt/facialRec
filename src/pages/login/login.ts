import { Component } from '@angular/core';
import { TranslateService } from '@ngx-translate/core';
import { IonicPage, NavController, ToastController } from 'ionic-angular';
import { Events } from 'ionic-angular';

//import { User } from '../../providers/providers';
import { QuickViewPage } from '../pages';

@IonicPage()
@Component({
  selector: 'page-login',
  templateUrl: 'login.html'
})
export class LoginPage {
  // The account fields for the login form.
  // If you're using the username field with or without email, make
  // sure to add it to the type
  account: { username: string, password: string } = {
    username: '',
    password: ''
  };
  /*account = JSON.stringify({
    username: 'UserName',
    password: 'password'
  });*/

  // Our translated text strings
  private loginErrorString: string;

  constructor(public navCtrl: NavController,
    public toastCtrl: ToastController,
    public translateService: TranslateService, public events: Events) {

    this.translateService.get('LOGIN_ERROR').subscribe((value) => {
      this.loginErrorString = value;
    })

    events.subscribe('native.keyboardshow', (e) => {
      document.getElementById("footer").style.display = "none";
    });
    events.subscribe('native.keyboardhide', (e) => {
      document.getElementById("footer").style.display = "block";
    });
  }

  ngAfterViewInit() {
    
  }

  public checkSubmit = function(){
    if(this.account.username != "" &&
      this.account.username != null &&
      this.account.password != "" &&
      this.account.password != null ){
        (<HTMLInputElement> document.getElementById("loginBtn")).disabled = false;
    }else{
      (<HTMLInputElement> document.getElementById("loginBtn")).disabled = true;
    }
  }

  public floatLabel = function(id){
      document.getElementById(id).style.transition = "all .5s ease";
      document.getElementById(id).style.transform = "translateY(-30px)";
      document.getElementById(id).style.animation = "sixPhasesFadeIn .5s";
      document.getElementById(id).style.opacity = "1";

  }
  public blurLabel = function(id){
  console.log(id);
  if(id == 'userIdLabel'){
      if(this.account.username != "" &&
      this.account.username != null){
      }else{
      document.getElementById(id).style.transition = "all .5s ease";
      document.getElementById(id).style.transform = "translateY(0)";
      document.getElementById(id).style.animation = "sixPhasesFadeOut .5s";
        document.getElementById(id).style.opacity = "0";
      }
}else{
      if(this.account.password != "" &&
      this.account.password != null){
      }else{
      document.getElementById(id).style.transition = "all .5s ease";
      document.getElementById(id).style.transform = "translateY(0)";
      document.getElementById(id).style.animation = "sixPhasesFadeOut .5s";
        document.getElementById(id).style.opacity = "0";
      }
      }
  }

  // open the selfie capture page
  doLogin() {
    this.navCtrl.push(QuickViewPage);
  }
}
