import { Component } from '@angular/core';
import { TranslateService } from '@ngx-translate/core';
import { IonicPage, NavController, ToastController } from 'ionic-angular';
import { QuickViewPage } from '../pages';
//import { MainPage } from '../pages';

@IonicPage()
@Component({
  selector: 'page-preferenceslanding',
  templateUrl: 'preferenceslanding.html'
})
export class PreferencesLandingPage {
  dateToday = new Date();
  locale = "en-us";
  month = this.dateToday.toLocaleString(this.locale, {month: "short"});
  day = this.dateToday.getDate();

  accounts = [
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company A', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company B', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company C', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company D', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company E', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company F', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company G', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company H', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company I', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company J', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company K', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company L', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company M', type: 'Other'},
    {desc: 'DEBIT CARD PURCHASE', from: 'spend', to:'Company N', type: 'Other'},

  ];

  constructor(public navCtrl: NavController) {

  }

  ngAfterViewInit() {

  }



  toQuickView() {
    this.navCtrl.push(QuickViewPage);
  }

}
