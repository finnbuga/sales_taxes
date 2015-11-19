<?php

class sales_taxes_product {

  /**
   * the product name
   * @var string
   */
  private $product;

  /**
   * the pre sales tax price
   * @var float
   */
  private $price;

  /**
   * the import status of the product: true if imported, false otherwise
   * @var bool
   */
  private $imported;

  /**
   * Constructor
   *
   * @param string $product the product name
   * @param float $price the pre sales tax price
   * @param bool $imported the import status of the product: true if imported, false otherwise
   */
  public function __construct($product, $price, $imported = false) {
    $this->product = $product;
    $this->price = $price;
    $this->imported = $imported;
  }

  /**
   * Get the basic sales tax
   *
   * @return float the resulting basic sales tax
   */
  public function   get_basic_sales_tax() {
    if (in_array($this->product, ['book', 'food', 'medical product'])) {
      return 0;
    }
    else {
      return $this->price / 10;
    }
  }

  /**
   * Get the import duty
   *
   * @return float the resulting import duty
   */
  public function get_import_duty() {
    if ($this->imported) {
      return $this->price * .05;
    }
    else {
      return 0;
    }
  }

  /**
   * Get the total sales tax
   *
   * @return float the resulting sales tax
   */
  public function get_total_sales_tax() {
    $total_tax = $this->get_basic_sales_tax() + $this->get_import_duty();
    return $this->get_rounded_up_to_0_05($total_tax);
  }

  /**
   * Get the rounded up value to the nearest 0.05
   *
   * @param  float $n
   * @return string the string representing the number with two decimal precision
   */
  private function get_rounded_up_to_0_05($n) {
    if (fmod($n, .05) == 0) {
      return $n;
    }
    else {
      return sprintf("%.2f", $n + (.05- fmod($n, .05)));
    }
  }
}