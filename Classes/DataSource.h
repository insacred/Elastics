//
//  DataSource.h
//  Cloudwatch
//
//  Created by Dmitri Goutnik on 21/12/2010.
//  Copyright 2010 Tundra Bot. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "EC2DescribeInstancesRequest.h"
#import "EC2Instance.h"

#import "MonitoringGetMetricStatisticsRequest.h"
#import "MonitoringDatapoint.h"

// Sent when all requests started by startAllRequests have completed
extern NSString *const kDataSourceAllRequestsCompletedNotification;

@interface DataSource : NSObject <AWSRequestDelegate> {
	NSDate									*_startedAt;
	NSDate									*_completedAt;
	NSMutableSet							*_runningRequests;
	EC2DescribeInstancesRequest				*_describeInstancesRequest;
	MonitoringGetMetricStatisticsRequest	*_getMetricStatisticsRequest;
}

+ (DataSource *)sharedInstance;

+ (NSDictionary *)defaultRequestOptions;
+ (void)setDefaultRequestOptions:(NSDictionary *)options;

// Start loading all requests in parallel
- (void)startAllRequests;
@property (nonatomic, retain, readonly) NSDate *startedAt;
@property (nonatomic, retain, readonly) NSDate *completedAt;

// Instances
- (void)describeInstances:(NSDictionary *)parameters;
@property (nonatomic, retain, readonly) NSArray *reservations;
@property (nonatomic, retain, readonly) NSArray *instances;

// Monitoring
- (void)getMetricStatistics:(NSDictionary *)parameters;
@property (nonatomic, retain, readonly) NSArray *datapoints;
@end