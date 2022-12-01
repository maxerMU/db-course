import { Component, OnInit } from '@angular/core';
import { StockDetailService } from '../stock-detail.service';
import { DetailInStock } from '../stock-detail';
import { Label } from '../left-bar/left-bar.component';
import { Router } from '@angular/router';

@Component({
  selector: 'app-order-form',
  templateUrl: './order-form.component.html',
  styleUrls: ['./order-form.component.less']
})
export class OrderFormComponent implements OnInit {
  order: DetailInStock = {part_number: '', quantity: 0}
  label: Label = Label.STOCK;

  constructor(private stockService: StockDetailService,
              private router: Router) { }

  ngOnInit(): void {
  }

  putDetail() {
    this.stockService.putDetailInStock(this.order).subscribe();
    this.router.navigateByUrl('/stock');
  }

  takeDetail() {
    this.stockService.takeDetailFromStock(this.order).subscribe();
    this.router.navigateByUrl('/stock');
  }

}
