#pragma once

//#include "../var.hdr.cxx"

//namespace noware
//{
	// Place in another project (kernel/os)?
	//namespace machine
	//{
			class dev //: misc::instance
			{
				public:
					dev (void);
					virtual ~dev (void);
					
					//virtual const noware::var evaluate (const noware::var &/* expression*/);
					virtual const std::string/* value*/ val (const std::string &/* expression*/, const std::string &/* (zyre) group*/ = grp_dft);
					
					//virtual const noware::var/* value*/ get (const noware::var &/* key*/) const;
					//virtual const bool/* success*/ set (const noware::var &/* key*/, const noware::var &/* value*/);
					
					// Transmit a message to one node.
					virtual const std::string/* response*/ unicast (const std::string &/* message*/, const std::string &/* peer (id)*/);
					
					// Transmit a message to multiple nodes.
					// Main usage: request other nodes to perform an operation.
					virtual const std::string/* response*/ multicast (const std::string &/* message*/, noware::nr &/* responses_count*//* number of peers who answered*/, const std::string &/* (zyre) group*/ = /*noware::machine::device::*/grp_dft, const std::string &/* filter*/ = "");
					
					static const std::string grp_dft;
				//protected:
					//static net::cluster nodes;
					//net::node node;
					zmq::zyre node;
				//protected:
				//private:
					// Manager of received messages.
					virtual void receive (const zyre_event_t */* zyre_event*/);
					
					// Receives responses from queries.
					//virtual const noware::var receive_local (const std::string &/* response_type*/, const std::string &/* filter*/ = "") const;
					virtual const std::string receive_local (noware::nr &/* responses_count*//* number of peers who answered*/, const std::string &/* (zyre) group (to receive from (where the message was sent to))*/ = /*noware::machine::device::*/grp_dft, const std::string &/* ^filter*/ = "") const;
					
					// Transmits responses to the thread who queried.
					virtual const bool unicast_local (const std::string &/* message*/) const;
					
					
					//
					// Only these functions
					// need to be implemented
					// by the inheriting class:
					//
					//virtual const noware::tree <>/* response*/ respond (const noware::tree <> &/* message*/);
					virtual const bool/* success*/ respond (const std::string &/* message*/, const zyre_event_t */* (zyre) event*/);
					virtual const bool/* success*/ search (std::string &/* result*/, const std::string &/* message/expression*/);// const
					virtual const bool/* success*/ search_local (std::string &/* result*/, const std::string &/* message/expression*/);// const
					virtual const std::string/* result*/ aggregate (const std::string &/* result*/, noware::nr &/* responses_count*//* number of peers who answered*/, const std::string &/* response*/, const std::string &/* expression*/);
			};
	//}
//}