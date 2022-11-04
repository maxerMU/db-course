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

@NgModule({
  declarations: [
    AppComponent,
    StockDetailsComponent,
    StockDetailComponent,
    LeftBarComponent,
    HeaderBarComponent,
    LoginComponent,
    OrdersComponent
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
