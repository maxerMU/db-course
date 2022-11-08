import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './login/login.component';
import { OrderFormComponent } from './order-form/order-form.component';
import { OrdersComponent } from './orders/orders.component';
import { SignupComponent } from './signup/signup.component';
import { StockDetailsComponent } from './stock-details/stock-details.component';
import { WorkersComponent } from './workers/workers.component';

const routes: Routes = [
  { path: 'stock', component: StockDetailsComponent },
  { path: 'orders', component: OrdersComponent },
  { path: 'workers', component: WorkersComponent },
  { path: 'orders/new', component: OrderFormComponent },
  { path: 'login', component: LoginComponent },
  { path: 'signup', component: SignupComponent },
  { path: '', redirectTo: '/stock', pathMatch: 'full' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
