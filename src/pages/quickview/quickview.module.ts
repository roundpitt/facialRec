import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { IonicPageModule } from 'ionic-angular';

import { QuickViewPage } from './quickview';

@NgModule({
  declarations: [
    QuickViewPage,
  ],
  imports: [
    IonicPageModule.forChild(QuickViewPage),
    TranslateModule.forChild()
  ],
  exports: [
    QuickViewPage
  ]
})
export class QuickViewPageModule { }
