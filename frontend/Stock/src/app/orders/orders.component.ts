import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Order } from '../order';
import { StockDetailService } from '../stock-detail.service';

@Component({
  selector: 'app-orders',
  templateUrl: './orders.component.html',
  styleUrls: ['./orders.component.less']
})
export class OrdersComponent implements OnInit {
  orders: Order[] = [];
  start_date: string = '';
  end_date: string = '';

  constructor(private stockService: StockDetailService,
              private router: Router) { 
              }

  ngOnInit(): void {
  }

  findOrders() {
    if (this.start_date.length != 0 && this.end_date.length != 0) {
      this.stockService.getOrders(this.start_date, this.end_date).subscribe(
        res => this.orders = res
      )
    }
  }

  newOrder() {
    this.router.navigateByUrl('/orders/new')
  }

}
