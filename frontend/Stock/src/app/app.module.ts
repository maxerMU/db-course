import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { StockDetailsComponent } from './stock-details/stock-details.component';
import { StockDetailComponent } from './stock-detail/stock-detail.component';
import { LeftBarComponent } from './left-bar/left-bar.component';
import { HeaderBarComponent } from './header-bar/header-bar.component';
import { LoginComponent } from './login/login.component';
import { AuthInterceptor } from './auth-interceptor';
import { OrdersComponent } from './orders/orders.component';
import { OrderFormComponent } from './order-form/order-form.component';
import { WorkersComponent } from './workers/workers.component';
import { SignupComponent } from './signup/signup.component';
import { BaseLayoutComponent } from './base-layout/base-layout.component';
import { SiteLayoutComponent } from './site-layout/site-layout.component';

@NgModule({
  declarations: [
    AppComponent,
    StockDetailsComponent,
    StockDetailComponent,
    LeftBarComponent,
    HeaderBarComponent,
    LoginComponent,
    OrdersComponent,
    OrderFormComponent,
    WorkersComponent,
    SignupComponent,
    BaseLayoutComponent,
    SiteLayoutComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [
    {provide: HTTP_INTERCEPTORS, useClass: AuthInterceptor, multi: true}
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
