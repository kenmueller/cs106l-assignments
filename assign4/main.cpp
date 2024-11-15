#include <algorithm>
#include <random>
#include <vector>

constexpr auto kMaxTempRequirement = 5.0;
constexpr auto uAvgTempRequirement = 60.0;

struct Forecast {
  double min_temp;
  double max_temp;
  double avg_temp;
};

Forecast compute_forecast(const std::vector<double>& dailyWeather) {
  if (dailyWeather.empty()) {
    return {0.0, 0.0, 0.0};
  }

  const auto min_temp = *std::min_element(dailyWeather.begin(), dailyWeather.end()),
             max_temp = *std::max_element(dailyWeather.begin(), dailyWeather.end()),
             sum = std::accumulate(dailyWeather.begin(), dailyWeather.end(), 0.0),
             avg_temp = sum / dailyWeather.size();

  return {min_temp, max_temp, avg_temp};
}

std::vector<Forecast> get_forecasts(const std::vector<std::vector<double>>& weatherData) {
  std::vector<Forecast> forecasts;
  forecasts.reserve(weatherData.size());

  std::transform(weatherData.begin(), weatherData.end(), std::back_inserter(forecasts),
                 compute_forecast);

  return forecasts;
}

std::vector<Forecast> get_filtered_data(const std::vector<Forecast>& forecastData) {
  std::vector<Forecast> filtered_forecasts = forecastData;

  const auto filter = [](const Forecast& forecast) {
    return !(((forecast.max_temp - forecast.min_temp) > kMaxTempRequirement) &&
             (forecast.avg_temp >= uAvgTempRequirement));
  };

  filtered_forecasts.erase(
      std::remove_if(filtered_forecasts.begin(), filtered_forecasts.end(), filter),
      filtered_forecasts.end());

  return filtered_forecasts;
}

std::vector<Forecast> get_shuffled_data(const std::vector<Forecast>& forecastData) {
  std::vector<Forecast> shuffled_forecasts = forecastData;

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(shuffled_forecasts.begin(), shuffled_forecasts.end(), g);

  return shuffled_forecasts;
}

std::vector<Forecast> run_weather_pipeline(const std::vector<std::vector<double>>& weatherData) {
  return get_shuffled_data(get_filtered_data(get_forecasts(weatherData)));
}

#include "utils.cpp"
