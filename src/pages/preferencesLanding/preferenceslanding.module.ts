import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { IonicPageModule } from 'ionic-angular';

import { PreferencesLandingPage } from './preferencesLanding';

@NgModule({
  declarations: [
    PreferencesLandingPage,
  ],
  imports: [
    IonicPageModule.forChild(PreferencesLandingPage),
    TranslateModule.forChild()
  ],
  exports: [
    PreferencesLandingPage
  ]
})
export class PreferencesLandingPageModule { }
