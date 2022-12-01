import { TestBed } from '@angular/core/testing';

import { StockDetailService } from './stock-detail.service';

describe('StockDetailService', () => {
  let service: StockDetailService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(StockDetailService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
