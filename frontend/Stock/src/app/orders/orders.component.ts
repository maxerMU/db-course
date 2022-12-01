import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Order } from '../order';
import { StockDetailService } from '../stock-detail.service';
import { Label } from '../left-bar/left-bar.component';

@Component({
  selector: 'app-orders',
  templateUrl: './orders.component.html',
  styleUrls: ['./orders.component.less']
})
export class OrdersComponent implements OnInit {
  label: Label = Label.ORDERS
  orders: Order[] = [];
  start_date: string = '2022-11-11';
  end_date: string = '';

  constructor(private stockService: StockDetailService,
              private router: Router) { 
              }

  ngOnInit(): void {
    this.start_date = new Date().toISOString().split('T')[0];
    this.end_date = new Date().toISOString().split('T')[0];
  }

  findOrders() {
    if (this.start_date.length != 0 && this.end_date.length != 0) {
      this.stockService.getOrders(this.start_date, this.end_date).subscribe(
        res => this.orders = res
      )
    }
  }

}
