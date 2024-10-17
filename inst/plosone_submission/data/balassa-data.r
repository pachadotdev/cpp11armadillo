finp <- "data/balassa-index.rds"

library(economiccomplexity)
library(RPostgres)
library(purrr)

finp <- "balassa-index.rds"

y <- 2002L:2020L

length(y)

con <- dbConnect(
  RPostgres::Postgres(),
  dbname = "tradestatistics", host = "localhost",
  port = 5432, user = "tradestatistics",
  password = Sys.getenv("TRADESTATISTICS_SQL_PWD")
)

trade <- map(
  y,
  function(y2) {
    tbl(con, "hs_rev2002_imports") %>%
      filter(year == y2) %>%
      group_by(country = partner_iso, product = commodity_code) %>%
      summarise(value = sum(trade_value_usd, na.rm = TRUE)) %>%
      filter(country != "0-unspecified") %>%
      collect()
  }
)

X <- map(
  seq_along(trade),
  function(i) {
    economiccomplexity:::country_product_aggregation(
      trade[[i]], "country", "product", "value"
    )
  }
)

X <- map(
  seq_along(X),
  function(i) {
    d <- economiccomplexity:::dataframe_to_matrix(X[[i]])
    as.matrix(d)
  }
)

mean(map_dbl(
  seq_along(X),
  function(i) { 
    ncol(X[[i]])
  }
))

mean(map_dbl(
  seq_along(X),
  function(i) {
    nrow(X[[i]])
  }
))

saveRDS(X, finp, compress = "xz")
