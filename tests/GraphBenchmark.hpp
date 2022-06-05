#pragma once

#include <vector>
#include <random>
#include <algorithm>

#include "../utilities/Timer.hpp"
#include "../structures/incidentMatrix/IncidentMatrix.hpp"
#include "../structures/neighborhoodList/NeighbourhoodList.hpp"

class GraphBenchmark {

public:
    enum Precision {NANOS, MICROS, MILIS, SECS};

    static void primIncidentMatrix(float density, int vertexCount);
    static void primNeighbourhoodList(float density, int vertexCount);

    static void kruskalIncidentMatrix(float density, int vertexCount);
    static void kruskalNeighbourhoodList(float density, int vertexCount);

    static void dijkstraIncidentMatrix(float density, int vertexCount);
    static void dijkstraNeighbourhoodList(float density, int vertexCount);

    static void bellmanIncidentMatrix(float density, int vertexCount);
    static void bellmanNeighbourhoodList(float density, int vertexCount);

    static void setRandomBoundaries(long low, long high) {
        lowRandom = low;
        highRandom = high;
    }

    static void setRetries(long count) {
        retries = count;
    }

    static void setPrecision(Precision precision) {
        printPrecision = precision;
    }

    static void setFileOutput(FILE* fileHandler) {
        file = fileHandler;
    }

    static void setGenerateCSV(bool value) {
        generateCSV = value;
    }

private:

    static long lowRandom;
    static long highRandom;
    static long retries;
    static Precision printPrecision;
    static const std::string resultDecorator;
    static FILE* file;
    static bool generateCSV;

    [[maybe_unused]]
    static void autoPrintBenchResults(
            const std::string& benchName,
            long vertexCount,
            float density,
            const std::vector<long>& timeMeasurements) {

        long min = *std::min_element(timeMeasurements.begin(), timeMeasurements.end());
        long max = *std::max_element(timeMeasurements.begin(), timeMeasurements.end());
        double avg = calculateAverage(timeMeasurements);

        printBenchResults(benchName, vertexCount, density, min, max, avg);
    }

    static void printBenchResults(
            const std::string& benchName,
            long vertexCount,
            float density,
            long min, long max, double avg) {

        const std::string* tp = getTimePrefix();

        if (generateCSV) {

            std::string benchNameCopy = benchName;

            std::replace(benchNameCopy.begin(), benchNameCopy.end(), ' ', '_');
            std::transform(benchNameCopy.begin(), benchNameCopy.end(), benchNameCopy.begin(), tolower);
            benchNameCopy.append(".csv");

            FILE* csv = fopen(benchNameCopy.c_str(), "a+");

            //check if file empty if so then append column headers
            int c = fgetc(csv);
            if (c == EOF)
                fprintf(csv, "%s,%s,%s,%s,%s\n", "N", "D", "Min", "Max", "Avg");


            fprintf(csv, "%ld,%.2f,%ld,%ld,%.2f\n", vertexCount, density, min, max, avg);

            fclose(csv);
        }

        if (file) {

            fprintf(file, "\n%s",
                    resultDecorator.c_str());
            fprintf(file, "%s, elements = %ld, density = %.2f, retries = %ld \n",
                   benchName.c_str(),
                   vertexCount,
                   density,
                   retries);
            fprintf(file, "Min = %ld %s/op, Max = %ld %s/op, Avg = %.2f %s/op \n",
                   min, tp->c_str(),
                   max, tp->c_str(),
                   avg,tp->c_str());
            fprintf(file, "%s",
                   resultDecorator.c_str());
        }

        printf("\n%s",
               resultDecorator.c_str());
        printf("%s, elements = %ld, density = %.2f, retries = %ld \n",
               benchName.c_str(),
               vertexCount,
               density,
               retries);
        printf("Min = %ld %s/op, Max = %ld %s/op, Avg = %.2f %s/op \n",
               min, tp->c_str(),
               max, tp->c_str(),
               avg,tp->c_str());
        printf("%s",
               resultDecorator.c_str());

        delete tp;
    }

    static const std::string* getTimePrefix() {

        switch (printPrecision) {
            case NANOS:
                return new std::string("ns");
            case MICROS:
                return new std::string("micros");
            case MILIS:
                return new std::string("ms");
            case SECS:
                return new std::string("s");
        }
        return new std::string("?");
    }

    static long getMatchingTimeResult(Timer& timer) {

        switch (printPrecision) {
            case NANOS:
                return timer.getNanos();
            case MICROS:
                return timer.getMicros();
            case MILIS:
                return timer.getMilis();
            case SECS:
                return timer.getSeconds();
            default:
                return timer.getNanos();
        }

    }

    static int randomInBounds() {
        return rand() % (highRandom - lowRandom) + highRandom;
    }

    static int randomInBounds(float coverage) {
        int middle = static_cast<int>(highRandom - lowRandom) / 2;
        int offset = (int) ((float)middle * coverage);
        int high = middle + offset;
        int low = middle - offset;

        return rand() % (high - low) + high;
    }

    static double calculateAverage(const std::vector<long>& timeResult) {
        long acc = 0;

        for (auto result : timeResult)
            acc += result;

        return (float)acc / (float)timeResult.size();
    }
};
