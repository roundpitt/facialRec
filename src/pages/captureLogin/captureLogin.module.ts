import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { IonicPageModule } from 'ionic-angular';

import { CaptureLoginPage } from './captureLogin';

@NgModule({
  declarations: [
    CaptureLoginPage,
  ],
  imports: [
    IonicPageModule.forChild(CaptureLoginPage),
    TranslateModule.forChild()
  ],
  exports: [
    CaptureLoginPage
  ]
})
export class CaptureLoginPageModule { }
