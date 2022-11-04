import { Component, OnInit } from '@angular/core';
import { DetailWithQuantity, StockDetailService } from '../stock-detail.service';
import { StockDetail } from '../stock-detail';

@Component({
  selector: 'app-stock-details',
  templateUrl: './stock-details.component.html',
  styleUrls: ['./stock-details.component.less'],
})
export class StockDetailsComponent implements OnInit {

  details: StockDetail[] = [];

  selectedDetail?: StockDetail;
  onSelect(detail: StockDetail): void {
    this.selectedDetail = detail;
  }

  constructor(private stockDetailService: StockDetailService) {
  }

  ngOnInit(): void {
    this.getDetails();
  }

  getDetails(): void {
    this.stockDetailService.getDetailsInStock().subscribe(details => this.details = details)
  }
}
