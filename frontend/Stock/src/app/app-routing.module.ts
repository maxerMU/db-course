import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './login/login.component';
import { OrdersComponent } from './orders/orders.component';
import { StockDetailsComponent } from './stock-details/stock-details.component';

const routes: Routes = [
  { path: 'stock', component: StockDetailsComponent },
  { path: 'orders', component: OrdersComponent },
  { path: 'login', component: LoginComponent },
  { path: '', redirectTo: '/stock', pathMatch: 'full' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
