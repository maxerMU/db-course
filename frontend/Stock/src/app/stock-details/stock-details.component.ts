import { Component, OnInit } from '@angular/core';
import { StockDetailService } from '../stock-detail.service';
import { DetailInStock } from '../stock-detail';
import { StockDetail } from '../stock-detail';
import { Label } from '../left-bar/left-bar.component';
import { Router } from '@angular/router';

@Component({
  selector: 'app-stock-details',
  templateUrl: './stock-details.component.html',
  styleUrls: ['./stock-details.component.less'],
})
export class StockDetailsComponent implements OnInit {

  details: StockDetail[] = [];
  label: Label = Label.STOCK;
  order: DetailInStock = {part_number: '', quantity: 1}

  selectedDetail?: StockDetail;
  onSelect(detail: StockDetail): void {
    this.selectedDetail = detail;
  }

  constructor(private stockDetailService: StockDetailService,
              private router: Router) {
  }

  ngOnInit(): void {
    this.getDetails();
  }

  getDetails(): void {
    this.stockDetailService.getDetailsInStock().subscribe(details => this.details = details)
  }

  newOrder() {
    this.router.navigateByUrl('/orders/new')
  }

  put(partNumber: string) {
    this.order.part_number = partNumber;
    this.stockDetailService.putDetailInStock(this.order).subscribe();
    let i = this.details.findIndex((el) => el.part_number == partNumber);
    this.details[i].amount += 1;
  }

  take(partNumber: string) {
    this.order.part_number = partNumber;
    this.stockDetailService.takeDetailFromStock(this.order).subscribe();
    let i = this.details.findIndex((el) => el.part_number == partNumber);
    this.details[i].amount -= 1;
  }
}
