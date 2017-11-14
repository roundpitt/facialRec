import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { IonicPageModule } from 'ionic-angular';

import { ZelleLandingPage } from './zelleLanding';

@NgModule({
  declarations: [
    ZelleLandingPage,
  ],
  imports: [
    IonicPageModule.forChild(ZelleLandingPage),
    TranslateModule.forChild()
  ],
  exports: [
    ZelleLandingPage
  ]
})
export class ZelleLandingPageModule { }
