//
//  ADBDownloadManager.h
//  v1.0.0
//
//  Created by Alberto De Bortoli on 27/08/2013.
//
//

#import <Foundation/Foundation.h>

@class ADBDownloadManager;

@protocol ADBDownloadManagerDataSource <NSObject>

@required

- (NSUInteger)numberOfFilesToDownloadForDownloadManager:(ADBDownloadManager *)manager;
- (NSString *)downloadManager:(ADBDownloadManager *)manager pathForFileToDownloadAtIndex:(NSUInteger)index;

@end

@protocol ADBDownloadManagerDelegate <NSObject>

@optional

- (void)downloadManager:(ADBDownloadManager *)manager
 didDownloadFileAtIndex:(NSUInteger)index
          fromRemoteURL:(NSString *)remoteURL
            toLocalPath:(NSString *)localPath
                  bytes:(NSUInteger)bytes;

- (void)downloadManager:(ADBDownloadManager *)manager
     didFailFileAtIndex:(NSUInteger)index
          fromRemoteURL:(NSString *)remoteURL
            toLocalPath:(NSString *)localPath
                  error:(NSError *)error;

- (void)downloadManagerDidCompleteAllDownloads:(ADBDownloadManager *)manager
                                    failedURLs:(NSArray *)failedURLs
                                    totalBytes:(NSUInteger)totalBytes;

- (void)downloadManagerWillStart:(ADBDownloadManager *)manager;

- (void)downloadManagerDidStop:(ADBDownloadManager *)manager;

@end

@interface ADBDownloadManager : NSObject

/**
 *	Designated initializer.
 *
 *	@param	baseRemoteURL	The base remote URL to use for the files to be downloaded.
 *	@param	localPathFolder	The base local path folder to use for the files to be saved.
 *	@param	queue	The queue to use for the execution of the NSURLConnection completionHandler.
 *
 *	@return	A ADBDownloadManager instance.
 */
- (instancetype)initWithBaseRemoteURL:(NSString *)baseRemoteURL localPathFolder:(NSString *)localPathFolder queue:(NSOperationQueue *)queue;

/**
 *	Start the download manager
 */
- (void)start;

/**
 *	Stop the download manager
 */
- (void)stop;

@property (nonatomic, weak) id<ADBDownloadManagerDataSource> dataSource;
@property (nonatomic, weak) id<ADBDownloadManagerDelegate> delegate;

/**
 *	If YES, the files are downloaded overwriting existing files on disk. If NO and files exist on disk, no download is performed and local copy is kept. The default value is NO.
 */
@property (nonatomic, assign) BOOL forceDownload;

/**
 *	The number of downloads in the current session.
 */
@property (nonatomic, readonly) NSUInteger numberOfDownloadsInSession;

@end