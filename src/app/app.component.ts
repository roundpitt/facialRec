import { Component, ViewChild } from '@angular/core';
import { SplashScreen } from '@ionic-native/splash-screen';
import { StatusBar } from '@ionic-native/status-bar';
import { TranslateService } from '@ngx-translate/core';
import { Config, Nav, Platform } from 'ionic-angular';

import { FirstRunPage } from '../pages/pages';
import { Settings } from '../providers/providers';

@Component({
  template: `<ion-menu side="right" [content]="content">
    <ion-content class="menu">
      <ion-list>
        <button menuClose ion-item *ngFor="let p of pages" (click)="openPage(p)">
        <ion-img width="15px" [src]="p.icon"></ion-img>
          {{p.title}}
        </button>
      </ion-list>
    </ion-content>

  </ion-menu>
  <ion-nav #content [root]="rootPage"></ion-nav>`
})
export class MyApp {
  rootPage = FirstRunPage;

  @ViewChild(Nav) nav: Nav;

  pages: any[] = [
    { title: 'Log Out', component: 'LoginPage', icon: 'assets/img/preferencesIcon.png'},
    { title: 'Pay Bills', component: 'LoginPage', icon: 'assets/img/payBillsIcon.png' },
    { title: 'Activity', component: 'LoginPage', icon: 'assets/img/activityIcon.png' },
    { title: 'Spending + Budgets', component: 'LoginPage', icon: 'assets/img/spendingIcon.png' },
    { title: 'Savings Engine', component: 'ZelleLandingPage', icon: 'assets/img/savingsIcon.png' },
    { title: 'Punch the Pig', component: 'ZelleLandingPage', icon: 'assets/img/pigIcon.png' },
    { title: 'Send Money with Zelle™', component: 'ZelleLandingPage', icon: 'assets/img/zelleIcon.png' },
    { title: 'Preferences', component: 'PreferencesLandingPage', icon: 'assets/img/preferencesIcon.png' },
    { title: 'Rewards & Offers', component: 'LoginPage', icon: 'assets/img/rewardsIcon.png' }
  ]

  constructor(private translate: TranslateService, platform: Platform, settings: Settings, private config: Config, private statusBar: StatusBar, private splashScreen: SplashScreen) {
    platform.ready().then(() => {
      // Okay, so the platform is ready and our plugins are available.
      // Here you can do any higher level native things you might need.
      this.statusBar.styleDefault();
      this.splashScreen.hide();
    });
    this.initTranslate();
  }

  initTranslate() {
    // Set the default language for translation strings, and the current language.
    this.translate.setDefaultLang('en');

    if (this.translate.getBrowserLang() !== undefined) {
      this.translate.use(this.translate.getBrowserLang());
    } else {
      this.translate.use('en'); // Set your language here
    }

    this.translate.get(['BACK_BUTTON_TEXT']).subscribe(values => {
      this.config.set('ios', 'backButtonText', values.BACK_BUTTON_TEXT);
    });
  }

  openPage(page) {
    // Reset the content nav to have just this page
    // we wouldn't want the back button to show in this scenario
    this.nav.setRoot(page.component);
  }
}
